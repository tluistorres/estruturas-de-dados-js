// Verificação para o console (aperte F12 no navegador para ver)
console.log("Script V2: Iniciando Show de Corações Coloridos!");

const canvas = document.getElementById('fireworksCanvas');
const ctx = canvas.getContext('2d');

let audioCtx = null;
let particles = [];
let fireworks = [];

// Redimensionamento automático
function resize() {
    canvas.width = window.innerWidth;
    canvas.height = window.innerHeight;
}
window.addEventListener('resize', resize);
resize();

// Função de Áudio: Sintetizador de Explosão
function playExplosionSound() {
    if (!audioCtx) return;
    if (audioCtx.state === 'suspended') audioCtx.resume();

    const osc = audioCtx.createOscillator();
    const gain = audioCtx.createGain();

    osc.type = 'triangle'; 
    // Frequência grave para impacto
    osc.frequency.setValueAtTime(170, audioCtx.currentTime);
    osc.frequency.exponentialRampToValueAtTime(0.01, audioCtx.currentTime + 0.5);

    gain.gain.setValueAtTime(0.5, audioCtx.currentTime);
    gain.gain.exponentialRampToValueAtTime(0.01, audioCtx.currentTime + 0.5);

    osc.connect(gain);
    gain.connect(audioCtx.destination);
    osc.start();
    osc.stop(audioCtx.currentTime + 0.5);
}

// Desbloqueia o áudio e oculta a mensagem inicial ao clicar
window.addEventListener('click', () => {
    if (!audioCtx) {
        audioCtx = new (window.AudioContext || window.webkitAudioContext)();
        const msg = document.getElementById('ui');
        if(msg) {
            msg.style.opacity = '0';
            setTimeout(() => msg.style.display = 'none', 500);
        }
    }
});

// Classe do Foguete que sobe (Launch)
class Firework {
    constructor() {
        this.x = Math.random() * canvas.width;
        this.y = canvas.height;
        this.targetY = Math.random() * (canvas.height / 2.5) + 50;
        
        // --- CORES COLORIDAS (Arco-Íris) ---
        // Escolhe um número de 0 a 360 (círculo cromático completo)
        this.hue = Math.floor(Math.random() * 360); 
        this.color = `hsl(${this.hue}, 100%, 60%)`; 
        
        this.speed = Math.random() * 1 + 3;
    }

    update() {
        this.y -= this.speed;
        if (this.y <= this.targetY) {
            this.explode();
            return true;
        }
        return false;
    }

    draw() {
        ctx.fillStyle = this.color;
        ctx.beginPath();
        ctx.arc(this.x, this.y, 3, 0, Math.PI * 2);
        ctx.fill();
    }

    explode() {
        playExplosionSound();
        const steps = 90; // Número de partículas para formar o coração
        for (let i = 0; i < steps; i++) {
            const t = (i / steps) * Math.PI * 2;
            
            // Equação Matemática do Coração (Cardioide)
            const x = 16 * Math.pow(Math.sin(t), 3);
            const y = -(13 * Math.cos(t) - 5 * Math.cos(2*t) - 2 * Math.cos(3*t) - Math.cos(4*t));
            
            // Passa a cor do foguete (hue) para as partículas
            particles.push(new HeartParticle(this.x, this.y, x, y, this.hue));
        }
    }
}

// Classe da Faísca em formato de coração
class HeartParticle {
    constructor(x, y, vx, vy, hue) {
        this.x = x;
        this.y = y;
        this.vx = vx * 0.5; // Ajusta o tamanho da explosão
        this.vy = vy * 0.5;
        this.hue = hue;
        this.life = 100;
        this.opacity = 1;
    }

    update() {
        this.x += this.vx;
        this.y += this.vy;
        this.vy += 0.04; // Gravidade suave
        this.life--;
        this.opacity = this.life / 100;
        
        // Efeito extra: a cor muda levemente enquanto cai (opcional)
        this.hue += 0.5; 
    }

    draw() {
        ctx.save();
        ctx.globalAlpha = this.opacity;
        ctx.fillStyle = `hsl(${this.hue}, 100%, 60%)`;
        
        // Efeito Neon (Glow)
        ctx.shadowBlur = 8;
        ctx.shadowColor = `hsl(${this.hue}, 100%, 60%)`;
        
        ctx.beginPath();
        ctx.arc(this.x, this.y, 2, 0, Math.PI * 2);
        ctx.fill();
        ctx.restore();
    }
}

// Loop de animação
function animate() {
    // Fundo semitransparente para criar o rastro (motion blur)
    ctx.fillStyle = 'rgba(0, 0, 0, 0.15)';
    ctx.fillRect(0, 0, canvas.width, canvas.height);

    // Lança novos fogos aleatoriamente
    if (Math.random() < 0.04) {
        fireworks.push(new Firework());
    }

    // Processa foguetes
    fireworks = fireworks.filter(f => {
        f.draw();
        return !f.update();
    });

    // Processa faíscas
    particles = particles.filter(p => {
        p.update();
        p.draw();
        return p.life > 0;
    });

    requestAnimationFrame(animate);
}

// Inicia o show
animate();

// Resumo Detalhado das Etapas do POST:

// O que fizemos foi um processo de exposição de recursos via requisições HTTP, saindo do modelo tradicional de arquivos locais para um modelo de transferência de rede.

// Etapa 1: Preparação do Payload (Conteúdo)

// O arquivo script_v2.js foi configurado como o nosso payload. Ele continha a lógica da Cardioide (matemática do coração) e as definições de cores HSL dinâmicas.

// Etapa 2: Tentativa de Upload Multipart/Form-Data (-F)

// Tentamos usar o curl com a flag -F (Form-data). Isso simula o comportamento de um formulário HTML onde você seleciona um arquivo.

// Comando: curl -F'file=@script_v2.js' https://0x0.st

// Barreira: O servidor identificou o User-Agent do curl e bloqueou por política de segurança.

// Etapa 3: Upload de Dados Binários Brutos (--data-binary)

// Para serviços como o paste.rs, envia
// mos o arquivo sem formatação de formulário, apenas jogando os bytes do arquivo diretamente no corpo da requisição POST.

// Comando: curl --data-binary @script_v2.js https://paste.rs

// Resultado: O servidor processou os dados, armazenou no banco de dados temporário e retornou um Endpoint (URL única) para acesso.

// Etapa 4: Transferência via TCP Puro (Netcat)

// Como alternativa ao protocolo HTTP, usamos o Termbin, que escuta conexões TCP na porta 9999. Ao dar um cat e um pipe (|) para o nc, enviamos o texto plano. O servidor do Termbin interpreta o fim da conexão como o fim do arquivo e gera a URL.

// Etapa 5: Exposição via Servidor Local (Escuta Ativa)

// Por fim, usamos o módulo http.server do Python. Em vez de você enviar (Push), você abriu uma porta (8085) para que outros pudessem puxar (Pull) o arquivo. Isso transforma seu Linux em um servidor de arquivos temporário.
